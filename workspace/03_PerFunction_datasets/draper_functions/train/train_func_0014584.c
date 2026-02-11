input_release_client_keys(Client *client)
{
	KeyReservation *kr;

	debug(RPT_DEBUG, "%s(client=[%d])", __FUNCTION__, (client ? client->sock : -1));

	for (kr = LL_GetFirst(keylist); kr != NULL; kr = LL_GetNext(keylist)) {
		if (kr->client == client) {
			report(RPT_INFO, "Key \"%.40s\" reserved %s by client [%d] and is now released",
				kr->key, (kr->exclusive ? "exclusively" : "shared"), (client ? client->sock : -1));
			free(kr->key);
			free(kr);

			LL_DeleteNode(keylist, PREV);
		}
	}
}
