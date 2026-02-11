perl_register_protocol(CHAT_PROTOCOL_REC *rec)
{
	static char *items[] = {
		"Chatnet",
		"Server", "ServerConnect", "ServerSetup",
		"Channel", "Query",
		"Nick"
	};
	static char *find_use_code =
		"my $pkg = Irssi::%s; $pkg =~ s/::/\\//;\n"
		"foreach my $i (@INC) {\n"
		"  return 1 if (-f \"$i/$pkg.pm\");\n"
		"}\n"
		"return 0;\n";

	char *name, stash[100], code[100], *pcode;
	int type, chat_type, n;
        SV *sv;

	chat_type = chat_protocol_lookup(rec->name);
	g_return_if_fail(chat_type >= 0);

	name = g_ascii_strdown(rec->name,-1);
	*name = *(rec->name);


	type = module_get_uniq_id_str("WINDOW ITEM TYPE", "CHANNEL");
	g_snprintf(stash, sizeof(stash), "Irssi::%s::Channel", name);
	irssi_add_object(type, chat_type, stash,
			 (PERL_OBJECT_FUNC) perl_channel_fill_hash);

	type = module_get_uniq_id_str("WINDOW ITEM TYPE", "QUERY");
	g_snprintf(stash, sizeof(stash), "Irssi::%s::Query", name);
	irssi_add_object(type, chat_type, stash,
			 (PERL_OBJECT_FUNC) perl_query_fill_hash);


	type = module_get_uniq_id("NICK", 0);
	g_snprintf(stash, sizeof(stash), "Irssi::%s::Nick", name);
	irssi_add_object(type, chat_type, stash,
			 (PERL_OBJECT_FUNC) perl_nick_fill_hash);


	type = module_get_uniq_id("CHATNET", 0);
	g_snprintf(stash, sizeof(stash), "Irssi::%s::Chatnet", name);
	irssi_add_object(type, chat_type, stash,
			 (PERL_OBJECT_FUNC) perl_chatnet_fill_hash);


	type = module_get_uniq_id("SERVER", 0);
	g_snprintf(stash, sizeof(stash), "Irssi::%s::Server", name);
	irssi_add_object(type, chat_type, stash,
			 (PERL_OBJECT_FUNC) perl_server_fill_hash);

	type = module_get_uniq_id("SERVER CONNECT", 0);
	g_snprintf(stash, sizeof(stash), "Irssi::%s::Connect", name);
	irssi_add_object(type, chat_type, stash,
			 (PERL_OBJECT_FUNC) perl_connect_fill_hash);


	for (n = 0; n < sizeof(items)/sizeof(items[0]); n++) {
		g_snprintf(code, sizeof(code),
			   "@Irssi::%s::%s::ISA = qw(Irssi::%s);",
			   name, items[n], items[n]);
		perl_eval_pv(code, TRUE);
	}

	pcode = g_strdup_printf(find_use_code, name);
	sv = perl_eval_pv(pcode, TRUE);
	g_free(pcode);

	if (SvIV(sv)) {
		use_protocols =
			g_slist_append(use_protocols, g_strdup(name));
	}

	g_free(name);
}
