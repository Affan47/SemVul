handle_immediate(struct tgsi_to_rc * ttr,
                             struct tgsi_full_immediate * imm,
                             unsigned index)
{
    struct rc_constant constant;
    unsigned swizzle = 0;
    boolean can_swizzle = TRUE;
    unsigned i;

    for (i = 0; i < 4; i++) {
        if (imm->u[i].Float == 0.0f) {
            swizzle |= RC_SWIZZLE_ZERO << (i * 3);
        } else if (imm->u[i].Float == 0.5f && ttr->use_half_swizzles) {
            swizzle |= RC_SWIZZLE_HALF << (i * 3);
        } else if (imm->u[i].Float == 1.0f) {
            swizzle |= RC_SWIZZLE_ONE << (i * 3);
        } else {
            can_swizzle = FALSE;
            break;
        }
    }

    if (can_swizzle) {
        ttr->imms_to_swizzle[ttr->imms_to_swizzle_count].index = index;
        ttr->imms_to_swizzle[ttr->imms_to_swizzle_count].swizzle = swizzle;
        ttr->imms_to_swizzle_count++;
    } else {
        constant.Type = RC_CONSTANT_IMMEDIATE;
        constant.Size = 4;
        for(i = 0; i < 4; ++i)
            constant.u.Immediate[i] = imm->u[i].Float;
        rc_constants_add(&ttr->compiler->Program.Constants, &constant);
    }
}
