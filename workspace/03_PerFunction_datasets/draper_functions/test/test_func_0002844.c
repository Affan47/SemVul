refs_clear_reloc(obj_header_t *hdr, uint size)
{
    ref_packed *rp = (ref_packed *) (hdr + 1);
    ref_packed *end = (ref_packed *) ((byte *) rp + size);

    while (rp < end) {
        if (r_is_packed(rp))
            rp++;
        else {

            ref *const pref = (ref *)rp;

            if (!ref_type_uses_size_or_null(r_type(pref))) {
                if_debug1('8', "  [8]clearing reloc at 0x%lx\n", (ulong) rp);
                r_set_size(pref, 0);
            }
            rp += packed_per_ref;
        }
    }
}
