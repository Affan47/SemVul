DumpRouteDelete(GF_SceneDumper *sdump, GF_Command *com)
{
	DUMP_IND(sdump);
	if (sdump->XMLDump) {
		fprintf(sdump->trace, "<Delete atRoute=\"");
		scene_dump_vrml_route_id(sdump, com->RouteID, com->def_name);
		fprintf(sdump->trace, "\"/>\n");
	} else {
		fprintf(sdump->trace, "DELETE ROUTE ");
		scene_dump_vrml_route_id(sdump, com->RouteID, com->def_name);
		fprintf(sdump->trace, "\n");
	}
	return GF_OK;
}
