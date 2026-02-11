PopulateDeoptimizationData(Handle<Code> code) {
  int length = deoptimizations_.length();
  if (length == 0) return;
  ASSERT(FLAG_deopt);
  Handle<DeoptimizationInputData> data =
      factory()->NewDeoptimizationInputData(length, TENURED);

  Handle<ByteArray> translations = translations_.CreateByteArray();
  data->SetTranslationByteArray(*translations);
  data->SetInlinedFunctionCount(Smi::FromInt(inlined_function_count_));

  Handle<FixedArray> literals =
      factory()->NewFixedArray(deoptimization_literals_.length(), TENURED);
  for (int i = 0; i < deoptimization_literals_.length(); i++) {
    literals->set(i, *deoptimization_literals_[i]);
  }
  data->SetLiteralArray(*literals);

  data->SetOsrAstId(Smi::FromInt(info_->osr_ast_id()));
  data->SetOsrPcOffset(Smi::FromInt(osr_pc_offset_));


  for (int i = 0; i < length; i++) {
    LEnvironment* env = deoptimizations_[i];
    data->SetAstId(i, Smi::FromInt(env->ast_id()));
    data->SetTranslationIndex(i, Smi::FromInt(env->translation_index()));
    data->SetArgumentsStackHeight(i,
                                  Smi::FromInt(env->arguments_stack_height()));
    data->SetPc(i, Smi::FromInt(env->pc_offset()));
  }
  code->set_deoptimization_data(*data);
}
