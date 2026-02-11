init_mteScalars(void)
{
    static oid      mteResource_oid[]    = { 1, 3, 6, 1, 2, 1, 88, 1, 1 };
    static oid      mteTriggerFail_oid[] = { 1, 3, 6, 1, 2, 1, 88, 1, 2, 1 };

    DEBUGMSGTL(("mteScalars", "Initializing\n"));

    netsnmp_register_scalar_group(
        netsnmp_create_handler_registration("mteResource", handle_mteResourceGroup,
                             mteResource_oid, OID_LENGTH(mteResource_oid),
                             HANDLER_CAN_RONLY),
        MTE_RESOURCE_SAMPLE_MINFREQ, MTE_RESOURCE_SAMPLE_LACKS);

    netsnmp_register_scalar(
        netsnmp_create_handler_registration("mteTriggerFailures",
                             handle_mteTriggerFailures,
                             mteTriggerFail_oid, OID_LENGTH(mteTriggerFail_oid),
                             HANDLER_CAN_RONLY));
}
