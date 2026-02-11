pc_or_size (char *in, uint64_t *out)
{
        uint32_t  pc = 0;
        int       ret = 0;

        if (gf_string2percent (in, &pc) == 0) {
                if (pc > 100) {
                        ret = gf_string2bytesize (in, out);
                } else {
                        *out = pc;
                }
        } else {
                ret = gf_string2bytesize (in, out);
        }
        return ret;
}
