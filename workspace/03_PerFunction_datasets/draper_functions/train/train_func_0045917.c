dump_sap(FILE *file,const char *label,struct atm_sap *sap)
{
    char buffer[MAX_ATM_SAP_LEN+1];
    int i;

    fprintf(file,"  %s ",label);
    if (sap2text(buffer,MAX_ATM_SAP_LEN+1,sap,S2T_NAME | S2T_LOCAL) >= 0)
	fprintf(file,"%s\n",buffer);
    else {
	fprintf(file,"<invalid:");
	for (i = 0; i < sizeof(*sap); i++)
	    fprintf(file," %02X",((unsigned char *) sap)[i]);
	fprintf(file,">\n");
    }
}
