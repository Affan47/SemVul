SCPI_CoreSre(scpi_t * context) {
    int32_t new_SRE;
    if (SCPI_ParamInt(context, &new_SRE, TRUE)) {
        SCPI_RegSet(context, SCPI_REG_SRE, new_SRE);
    }
    return SCPI_RES_OK;
}
