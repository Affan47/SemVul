generateEvalCode(CompileState* comp)
{
    OpValue v = loc->valueForTypeOf(comp);

    OpValue out;
    CodeGen::emitOp(comp, Op_TypeOf, &out, &v);
    return out;
}
