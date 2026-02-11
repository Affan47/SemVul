PR_PopIOLayer(PRFileDesc *stack, PRDescIdentity id)
{
    PRFileDesc *extract = PR_GetIdentitiesLayer(stack, id);

    PR_ASSERT(0 != id);
    PR_ASSERT(NULL != stack);
    PR_ASSERT(NULL != extract);
    if ((NULL == stack) || (0 == id) || (NULL == extract))
    {
        PR_SetError(PR_INVALID_ARGUMENT_ERROR, 0);
        return NULL;
    }

    if (extract == stack) {


        PRFileDesc copy = *stack;
        extract = stack->lower;
        *stack = *extract;
        *extract = copy;
        stack->higher = NULL;
        if (stack->lower) {
            PR_ASSERT(stack->lower->higher == extract);
            stack->lower->higher = stack;
        }
	} else if ((PR_IO_LAYER_HEAD == stack->identity) &&
					(extract == stack->lower) && (extract->lower == NULL)) {


			stack->lower = NULL;
			_PR_DestroyIOLayer(stack);
	} else {

        extract->lower->higher = extract->higher;
        extract->higher->lower = extract->lower;
    }
    extract->higher = extract->lower = NULL;
    return extract;
}
