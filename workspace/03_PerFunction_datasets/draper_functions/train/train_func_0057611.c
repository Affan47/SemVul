bios_10_4f02(struct regs *regs)
{
        CONST struct cirrus_mode_info *miblock;

#if CIRRUS_DEBUG & CIRRUS_DEBUG_VESA_2
        dprintf("Cirrus VESA Function 02 called.\n");
#endif
#if CIRRUS_DEBUG & CIRRUS_DEBUG_VESA_2_DETAILS
        CIRRUS_DEBUG_DUMP_REGS;
#endif

        if (BX & 0x3600) {

                AX = VBE_UNIMPLEMENTED;
#ifdef CIRRUS_WARNINGS
                dprintf("WARNING: Cirrus BIOS: bios_10_4f02: Default ");
                dprintf("zeroes not zero! Ignoring mode set.\n");
#endif
                return;
        }

        if ((BX & 0x1ff) < 0x100) {


#if CIRRUS_DEBUG & CIRRUS_DEBUG_VESA_2
                dprintf("  Switching to legacy mode...\n");
#endif


                miblock = _cirrus_find_miblock(CIRRUS_FALLBACK_MODE);
                _cirrus_switch_mode(miblock);

                outw(BL, 0x03de);
                outw(0, 0x03dc);
                set_mode(BL);

                AX = VBE_SUCCESS;
                return;
        }


        if (!(miblock = _cirrus_find_miblock(BX & 0x1ff))) {
#ifdef CIRRUS_WARNINGS
                dprintf("WARNING: Cirrus BIOS: bios_10_4f02: Couldn't find ");
                dprintf("requested mode in list! Ignoring mode set.\n");
#endif
                AX = VBE_UNIMPLEMENTED;
                return;
        }

        _cirrus_switch_mode(miblock);

        if (!(BX & 0x4000)) {

                _cirrus_enable_16k_granularity();
        }


        if (!(BX & 0x8000)) {
                _cirrus_clear_display(miblock);
        }


        var_put(vbe_mode, BX);

        AX = VBE_SUCCESS;
}
