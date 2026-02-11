generateUncaughtError()
{
    Expression *e = (*thrown->value->elements)[0];
    StringExp* se = e->toString();
    thrown->error("Uncaught CTFE exception %s(%s)", thrown->type->toChars(), se ? se->toChars() : e->toChars());


    if (loc.filename && !loc.equals(thrown->loc))
        errorSupplemental(loc, "thrown from here");
}
