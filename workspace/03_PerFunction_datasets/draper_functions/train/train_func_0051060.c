config_requires(ConfigArgs *c) {
	slap_mask_t requires = frontendDB->be_requires;
	int i, argc = c->argc;
	char **argv = c->argv;

	slap_verbmasks requires_ops[] = {
		{ BER_BVC("bind"),		SLAP_REQUIRE_BIND },
		{ BER_BVC("LDAPv3"),		SLAP_REQUIRE_LDAP_V3 },
		{ BER_BVC("authc"),		SLAP_REQUIRE_AUTHC },
		{ BER_BVC("sasl"),		SLAP_REQUIRE_SASL },
		{ BER_BVC("strong"),		SLAP_REQUIRE_STRONG },
		{ BER_BVNULL, 0 }
	};
	if (c->op == SLAP_CONFIG_EMIT) {
		return mask_to_verbs( requires_ops, c->be->be_requires, &c->rvalue_vals );
	} else if ( c->op == LDAP_MOD_DELETE ) {
		if ( !c->line ) {
			c->be->be_requires = 0;
		} else {
			i = verb_to_mask( c->line, requires_ops );
			c->be->be_requires &= ~requires_ops[i].mask;
		}
		return 0;
	}

	if ( strcasecmp( c->argv[ 1 ], "none" ) == 0 ) {
		argv++;
		argc--;
		requires = 0;
	}
	i = verbs_to_mask(argc, argv, requires_ops, &requires);
	if ( i ) {
		if (strcasecmp( c->argv[ i ], "none" ) == 0 ) {
			snprintf( c->cr_msg, sizeof( c->cr_msg ), "<%s> \"none\" (#%d) must be listed first", c->argv[0], i - 1 );
			Debug(LDAP_DEBUG_ANY, "%s: %s\n",
				c->log, c->cr_msg, 0);
		} else {
			snprintf( c->cr_msg, sizeof( c->cr_msg ), "<%s> unknown feature #%d", c->argv[0], i - 1 );
			Debug(LDAP_DEBUG_ANY, "%s: %s \"%s\"\n",
				c->log, c->cr_msg, c->argv[i]);
		}
		return(1);
	}
	c->be->be_requires = requires;
	return(0);
}
