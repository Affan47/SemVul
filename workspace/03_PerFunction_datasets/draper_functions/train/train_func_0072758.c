requestTemporary(OpType type, OpValue* value, OpValue* reference)
{
    ASSERT(type == OpType_value || type == OpType_bool || type == OpType_int32 || type == OpType_number);

    value->type      = type;
    value->immediate = false;

    reference->type      = OpType_reg;
    reference->immediate = true;

    RegDescriptor* temp = 0;

    bool markable = (type == OpType_value);

    if (markable && !freeMarkTemps.isEmpty()) {
        temp = freeMarkTemps.last();
        freeMarkTemps.removeLast();
    } else if (!markable && !freeNonMarkTemps.isEmpty()) {
        temp = freeNonMarkTemps.last();
        freeNonMarkTemps.removeLast();
    }

    if (!temp) {
        Register id = maxTemp;
        fbody->reserveSlot(id, markable);
        temp = new RegDescriptor(this, id, markable);
        ++maxTemp;
    }

    value->ownedReg = temp;

    reference->ownedReg = temp;
    reference->value.narrow.regVal = temp->reg();
}
