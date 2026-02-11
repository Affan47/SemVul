pssh_dump(GF_Box *a, FILE * trace)
{
	GF_ProtectionSystemHeaderBox *ptr = (GF_ProtectionSystemHeaderBox*) a;
	if (!a) return GF_BAD_PARAM;

	fprintf(trace, "<ProtectionSystemHeaderBox SystemID=\"");
	DumpData(trace, ptr->SystemID, 16);
	fprintf(trace, "\">\n");
	DumpBox(a, trace);
	gf_full_box_dump((GF_Box *)a, trace);

	if (ptr->KID_count) {
		u32 i;
		for (i=0; i<ptr->KID_count; i++) {
			fprintf(trace, " <PSSHKey KID=\"");
			DumpData(trace, ptr->KIDs[i], 16);
			fprintf(trace, "\"/>\n");
		}
	}
	if (ptr->private_data_size) {
		fprintf(trace, " <PSSHData size=\"%d\" value=\"", ptr->private_data_size);
		DumpData(trace, ptr->private_data, ptr->private_data_size);
		fprintf(trace, "\"/>\n");
	}
	gf_box_dump_done("ProtectionSystemHeaderBox", a, trace);
	return GF_OK;
}
