_store_reg(HDMV_VM *p, uint32_t reg, uint32_t val)
{
    if (!_is_valid_reg(reg)) {
        BD_DEBUG(DBG_HDMV, "_store_reg(): invalid register 0x%x\n", reg);
        return -1;
    }

    if (reg & PSR_FLAG) {
        BD_DEBUG(DBG_HDMV, "_store_reg(): storing to PSR is not allowed\n");
        return -1;
    }  else {
        return bd_gpr_write(p->regs, reg, val);
    }
}
