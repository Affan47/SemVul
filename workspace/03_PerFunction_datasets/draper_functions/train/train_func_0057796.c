clish_shell_pop_file(clish_shell_t *this)
{
    bool_t              result = BOOL_FALSE;
    clish_shell_file_t *node   = this->current_file;

    if(node)
    {


        this->current_file = node->next;


        fclose(node->file);

        if(node->next)
        {

            tinyrl__set_istream(this->tinyrl,node->next->file);
            result = BOOL_TRUE;
        }

        free(node);
    }
    return result;
}
