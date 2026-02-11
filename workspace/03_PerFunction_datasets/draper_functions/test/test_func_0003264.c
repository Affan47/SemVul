destructor(stmt_ty *that)
{
    stmt_define_ty  *this;

    this = (stmt_define_ty *)that;
    if (this->first)
        blob_free(this->first);
    blob_list_free(this->body);
}
