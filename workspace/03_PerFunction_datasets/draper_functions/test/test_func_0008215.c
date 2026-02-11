deleteDoc(const char* id)
{
    return (command("DELE %s%s"
	, id[0] == '/' || strncmp(id, FAX_DOCDIR, sizeof (FAX_DOCDIR)-1) == 0 ?
	    "" : "/" FAX_DOCDIR "/"
	, id
	) == COMPLETE);
}
