check_proposal(private_proposal_t *this)
{
	enumerator_t *e;
	entry_t *entry;
	u_int16_t alg, ks;
	bool all_aead = TRUE;
	int i;

	if (this->protocol == PROTO_IKE)
	{
		e = create_enumerator(this, PSEUDO_RANDOM_FUNCTION);
		if (!e->enumerate(e, &alg, &ks))
		{


			e->destroy(e);
			e = create_enumerator(this, INTEGRITY_ALGORITHM);
			while (e->enumerate(e, &alg, &ks))
			{
				for (i = 0; i < countof(integ_prf_map); i++)
				{
					if (alg == integ_prf_map[i].integ)
					{
						add_algorithm(this, PSEUDO_RANDOM_FUNCTION,
									  integ_prf_map[i].prf, 0);
						break;
					}
				}
			}
		}
		e->destroy(e);
	}

	if (this->protocol == PROTO_ESP)
	{
		e = create_enumerator(this, ENCRYPTION_ALGORITHM);
		while (e->enumerate(e, &alg, &ks))
		{
			if (!encryption_algorithm_is_aead(alg))
			{
				all_aead = FALSE;
				break;
			}
		}
		e->destroy(e);

		if (all_aead)
		{


			e = array_create_enumerator(this->transforms);
			while (e->enumerate(e, &entry))
			{
				if (entry->type == INTEGRITY_ALGORITHM)
				{
					array_remove_at(this->transforms, e);
				}
			}
			e->destroy(e);
		}
	}

	if (this->protocol == PROTO_AH || this->protocol == PROTO_ESP)
	{
		e = create_enumerator(this, EXTENDED_SEQUENCE_NUMBERS);
		if (!e->enumerate(e, NULL, NULL))
		{
			add_algorithm(this, EXTENDED_SEQUENCE_NUMBERS, NO_EXT_SEQ_NUMBERS, 0);
		}
		e->destroy(e);
	}

	array_compress(this->transforms);
}
