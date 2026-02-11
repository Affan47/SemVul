regalloc(CodeGenerator *cg) {
    for (int i = 0 ; i < NOPERS ; i++) {
        IFNode *op = ops[i] ;
        if (op != NULL) {
           if (op->reg != NULL) {
               IFExpression *expr = dynamic_cast<IFExpression*>(op) ;
               expr->uses-- ;
               if (expr->uses <= 0) {
                   cg->freeReg (op->reg) ;
               }
            }
        }
    }
}
