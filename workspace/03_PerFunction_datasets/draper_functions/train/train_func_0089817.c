callerGetter(ExecState* exec, JSObject*, const Identifier&, const PropertySlot& slot)
{
    FunctionImp* thisObj = static_cast<FunctionImp*>(slot.slotBase());
    ExecState* context = exec;
    while (context) {
        if (context->function() == thisObj)
            break;
        context = context->callingExecState();
    }

    if (!context)
        return jsNull();

    ExecState* callingContext = context->callingExecState();
    if (!callingContext)
        return jsNull();

    FunctionImp* callingFunction = callingContext->function();
    if (!callingFunction)
        return jsNull();

    return callingFunction;
}
