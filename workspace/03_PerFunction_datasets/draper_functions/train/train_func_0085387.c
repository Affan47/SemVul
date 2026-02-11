regUpdateSTB(scpi_t * context, scpi_reg_val_t val, scpi_reg_name_t mask, scpi_reg_val_t stbBits) {
    if (val & SCPI_RegGet(context, mask)) {
        SCPI_RegSetBits(context, SCPI_REG_STB, stbBits);
    } else {
        SCPI_RegClearBits(context, SCPI_REG_STB, stbBits);
    }
}
