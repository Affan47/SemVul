plpgsql_parse_dblword(const char *word)
{
	PLpgSQL_nsitem *ns;
	char	   *cp[2];
	int			nnames;


	plpgsql_convert_ident(word, cp, 2);


	ns = plpgsql_ns_lookup(cp[0], cp[1], NULL, &nnames);
	if (ns == NULL)
	{
		pfree(cp[0]);
		pfree(cp[1]);
		return T_ERROR;
	}

	switch (ns->itemtype)
	{
		case PLPGSQL_NSTYPE_VAR:

			plpgsql_yylval.scalar = plpgsql_Datums[ns->itemno];
			pfree(cp[0]);
			pfree(cp[1]);
			return T_SCALAR;

		case PLPGSQL_NSTYPE_REC:
			if (nnames == 1)
			{


				PLpgSQL_recfield *new;

				new = palloc(sizeof(PLpgSQL_recfield));
				new->dtype = PLPGSQL_DTYPE_RECFIELD;
				new->fieldname = pstrdup(cp[1]);
				new->recparentno = ns->itemno;

				plpgsql_adddatum((PLpgSQL_datum *) new);

				plpgsql_yylval.scalar = (PLpgSQL_datum *) new;

				pfree(cp[0]);
				pfree(cp[1]);
				return T_SCALAR;
			}
			else
			{

				plpgsql_yylval.rec = (PLpgSQL_rec *) (plpgsql_Datums[ns->itemno]);
				pfree(cp[0]);
				pfree(cp[1]);
				return T_RECORD;
			}

		case PLPGSQL_NSTYPE_ROW:
			if (nnames == 1)
			{


				PLpgSQL_row *row;
				int			i;

				row = (PLpgSQL_row *) (plpgsql_Datums[ns->itemno]);
				for (i = 0; i < row->nfields; i++)
				{
					if (row->fieldnames[i] &&
						strcmp(row->fieldnames[i], cp[1]) == 0)
					{
						plpgsql_yylval.scalar = plpgsql_Datums[row->varnos[i]];
						pfree(cp[0]);
						pfree(cp[1]);
						return T_SCALAR;
					}
				}
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_COLUMN),
						 errmsg("row \"%s\" has no field \"%s\"",
								cp[0], cp[1])));
			}
			else
			{

				plpgsql_yylval.row = (PLpgSQL_row *) (plpgsql_Datums[ns->itemno]);
				pfree(cp[0]);
				pfree(cp[1]);
				return T_ROW;
			}

		default:
			break;
	}

	pfree(cp[0]);
	pfree(cp[1]);
	return T_ERROR;
}
