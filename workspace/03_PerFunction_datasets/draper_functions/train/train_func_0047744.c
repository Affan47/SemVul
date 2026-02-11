fp_record_update(fp_record_ty *this, fp_value_ty *fp)
{
    trace(("fp_record_update(this = %p, fp = %p)\n{\n", this, fp));
    if (!this->exists || !fp_value_equal_all(&this->value, fp))
    {
        trace(("need to update\n"));
        this->exists = 1;
        fp_subdir_dirty_notify(this->parent, this->filename);
        fp_value_copy(&this->value, fp);
    }
    trace(("}\n"));
}
