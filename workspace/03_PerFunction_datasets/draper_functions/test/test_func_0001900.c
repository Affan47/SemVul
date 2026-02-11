type_of(int field)
{
    switch (field) {
	case F_VCC:
	case F_LISTEN_VCC:
	    return vt_vcc;
	case F_REPLY:
	    return vt_error;
	case F_PVC:
	    return vt_pvc;
	case F_LOCAL:
	case F_SVC:
	    return vt_svc;
	case F_QOS:
	    return vt_qos;
	case F_SAP:
	    return vt_sap;
	default:
	    fprintf(stderr,"unexpected field type 0x%x\n",field);
	    exit(1);
    }
}
