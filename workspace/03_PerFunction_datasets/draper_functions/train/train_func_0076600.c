GetLastDamagedPart (edict_t * self, char *buf)
{
	switch(self->client->resp.last_damaged_part) {
	case LOC_HDAM:
		strcpy (buf, "head");
		break;
	case LOC_CDAM:
		strcpy (buf, "chest");
		break;
	case LOC_SDAM:
		strcpy (buf, "stomach");
		break;
	case LOC_LDAM:
		strcpy (buf, "legs");
		break;
	case LOC_KVLR_HELMET:
		strcpy (buf, "kevlar helmet");
		break;
	case LOC_KVLR_VEST:
		strcpy (buf, "kevlar vest");
		break;
	case LOC_NO:
		strcpy (buf, "body");
		break;
	default:
		strcpy (buf, "nothing");
		break;
	}
	self->client->resp.last_damaged_part = 0;
}
