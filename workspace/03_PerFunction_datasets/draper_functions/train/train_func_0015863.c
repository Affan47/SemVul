fp_value_write(fp_value_ty *this, string_ty *key, FILE *fp)
{
    if (!this->contents_fingerprint && !this->ingredients_fingerprint)
        return;
    trace(("fp_value_write(this = %08lX, key = \"%s\", fp = %08lX)\n{\n",
        (long)this, key->str_text, (long)fp));
    fprintf(fp, "\"%s\" = { %ld", key->str_text, (long)this->oldest);
    if (this->oldest != this->newest || this->newest != this->stat_mod_time)
    {
        fprintf(fp, " %ld", (long)this->newest);
        if (this->newest != this->stat_mod_time)
            fprintf(fp, " %ld", (long)this->stat_mod_time);
    }
    fprintf
    (
        fp,
        "\n\"%s\"",
        (this->contents_fingerprint ? this->contents_fingerprint->str_text : "")
    );
    if (this->ingredients_fingerprint)
    {
        fprintf(fp, "\n\"%s\"", this->ingredients_fingerprint->str_text);
    }
    fprintf(fp, " }\n");
    trace(("}\n"));
}
