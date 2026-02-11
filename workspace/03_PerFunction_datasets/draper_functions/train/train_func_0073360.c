emitContextDecision(raw_ostream &o1, raw_ostream &o2,
                                             unsigned &i1, unsigned &i2,
                                             unsigned &ModRMTableNum,
                                             ContextDecision &decision,
                                             const char* name) const {
  o2.indent(i2) << "static const struct ContextDecision " << name << " = {\n";
  i2++;
  o2.indent(i2) << "{ /* opcodeDecisions */" << "\n";
  i2++;

  for (unsigned index = 0; index < IC_max; ++index) {
    o2.indent(i2) << "/* ";
    o2 << stringForContext((InstructionContext)index);
    o2 << " */";
    o2 << "\n";

    emitOpcodeDecision(o1, o2, i1, i2, ModRMTableNum,
                       decision.opcodeDecisions[index]);

    if (index + 1 < IC_max)
      o2 << ", ";
  }

  i2--;
  o2.indent(i2) << "}" << "\n";
  i2--;
  o2.indent(i2) << "};" << "\n";
}
