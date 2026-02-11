createCodeEmitterGK110(Program::Type type)
{
   CodeEmitterGK110 *emit = new CodeEmitterGK110(this);
   emit->setProgramType(type);
   return emit;
}

}
