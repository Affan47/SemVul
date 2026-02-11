currently_called_function (void)
{
    fncall *call = current_function_call();

    return (call != NULL)? call->fun : NULL;
}
