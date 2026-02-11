delete_alias_list(const struct RegisterTable* ptr)
{   RegisterAliasList*  p = ptr->alias;
    RegisterAliasList*  next;

    while   (p != NULL)
    {   if  (p->operand != NULL)
        {   delete_operand(p->operand);
        }
        next = p->next;
        free(p);
        p = next;
    }
}
