new_sv_for_xfer(
    Xfer *xfer)
{
    if (!xfer) return &PL_sv_undef;

    xfer_ref(xfer);
    return new_sv_for_c_obj(xfer, "Amanda::Xfer::Xfer");
}
