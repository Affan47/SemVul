glusterd_need_brick_op (glusterd_op_t op)
{
        gf_boolean_t ret        = _gf_false;

        GF_ASSERT (GD_OP_NONE < op && op < GD_OP_MAX);

        switch (op) {
        case GD_OP_PROFILE_VOLUME:
        case GD_OP_STATUS_VOLUME:
        case GD_OP_DEFRAG_BRICK_VOLUME:
        case GD_OP_HEAL_VOLUME:
                ret = _gf_true;
                break;
        default:
                ret = _gf_false;
        }

        return ret;
}
