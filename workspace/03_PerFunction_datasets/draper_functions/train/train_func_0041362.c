get_sd(DBusMessage *rep, int msgid)
{
	int ret, i, k;
	struct cm_tdbusm_dict **d;
	char *s;
	ret = cm_tdbusm_get_sd(rep, NULL, &s, &d);
	if (ret == 0) {
		printf("Message %d - s:%s,[", msgid, s);
		for (i = 0; (d != NULL) && (d[i] != NULL); i++) {
			printf("%s{%s=", i > 0 ? "," : "", d[i]->key);
			switch (d[i]->value_type) {
			case cm_tdbusm_dict_s:
				printf("s:%s}", d[i]->value.s);
				break;
			case cm_tdbusm_dict_p:
				printf("p:%s}", d[i]->value.s);
				break;
			case cm_tdbusm_dict_as:
				printf("as:[");
				for (k = 0;
				     (d[i]->value.as != NULL) &&
				     (d[i]->value.as[k] != NULL);
				     k++) {
					printf("%s%s", k > 0 ? "," : "",
					       d[i]->value.as[k]);
				}
				printf("]");
				break;
			case cm_tdbusm_dict_n:
				printf("n:%ld}", d[i]->value.n);
				break;
			case cm_tdbusm_dict_b:
				printf("b:%s}",
				       d[i]->value.b ? "TRUE" : "FALSE");
				break;
			}
		}
		printf("]\n");
	}
	return ret;
}
