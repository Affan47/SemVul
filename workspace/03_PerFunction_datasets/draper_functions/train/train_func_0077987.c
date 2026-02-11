replace_temp_operand_inorder(RfmQuad start,
                             RfmOperand before,
                             RfmOperand after)
{
    RfmQuad quad;

    if ((before->kind == RFM_KIND_TEMP) &&
        (after->kind == RFM_KIND_TEMP)) {

    } else {
        return (FALSE);
    }
    for (quad = start; quad; quad = quad->next) {
        if (replace_temp_operand(quad, before, after)) {
            return (TRUE);
        }
    }
    return (FALSE);
}
