merge_stack(context_type *context, unsigned int from_inumber,
            unsigned int to_inumber, stack_info_type *new_stack_info)
{
    instruction_data_type *idata = context->instruction_data;
    instruction_data_type *this_idata = &idata[to_inumber];

    int new_stack_size =  new_stack_info->stack_size;
    stack_item_type *new_stack = new_stack_info->stack;

    int stack_size = this_idata->stack_info.stack_size;

    if (stack_size == UNKNOWN_STACK_SIZE) {

        this_idata->stack_info.stack_size = new_stack_size;
        this_idata->stack_info.stack = new_stack;
        this_idata->changed = JNI_TRUE;
    } else if (new_stack_size != stack_size) {
        CCerror(context, "Inconsistent stack height %d != %d",
                new_stack_size, stack_size);
    } else {
        stack_item_type *stack = this_idata->stack_info.stack;
        stack_item_type *old, *new;
        jboolean change = JNI_FALSE;
        for (old = stack, new = new_stack; old != NULL;
                   old = old->next, new = new->next) {
            if (!isAssignableTo(context, new->item, old->item)) {
                change = JNI_TRUE;
                break;
            }
        }
        if (change) {
            stack = copy_stack(context, stack);
            for (old = stack, new = new_stack; old != NULL;
                          old = old->next, new = new->next) {
                if (new == NULL) {
                    break;
                }
                old->item = merge_fullinfo_types(context, old->item, new->item,
                                                 JNI_FALSE);
                if (GET_ITEM_TYPE(old->item) == ITEM_Bogus) {
                        CCerror(context, "Mismatched stack types");
                }
            }
            if (old != NULL || new != NULL) {
                CCerror(context, "Mismatched stack types");
            }
            this_idata->stack_info.stack = stack;
            this_idata->changed = JNI_TRUE;
        }
    }
}
