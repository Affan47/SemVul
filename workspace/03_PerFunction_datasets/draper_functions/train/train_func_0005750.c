loadstore (IFExpression *ex) {
    Instruction inst (ex->fenode, ex->opcode) ;
    setDest (inst, ex) ;
    inst.setOperand (0, operand (ex->ops[0])) ;
    if (ex->ops[1] != NULL) {
        inst.setOperand (1, operand (ex->ops[1])) ;
    }
    issue (inst) ;
}
