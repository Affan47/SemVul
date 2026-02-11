ComputeSlotMappingForArguments(JavaScriptFrame* frame,
                                           int inlined_frame_index,
                                           Vector<SlotRef>* args_slots) {
  AssertNoAllocation no_gc;
  int deopt_index = AstNode::kNoNumber;
  DeoptimizationInputData* data =
      static_cast<OptimizedFrame*>(frame)->GetDeoptimizationData(&deopt_index);
  TranslationIterator it(data->TranslationByteArray(),
                         data->TranslationIndex(deopt_index)->value());
  Translation::Opcode opcode = static_cast<Translation::Opcode>(it.Next());
  ASSERT(opcode == Translation::BEGIN);
  int frame_count = it.Next();
  USE(frame_count);
  ASSERT(frame_count > inlined_frame_index);
  int frames_to_skip = inlined_frame_index;
  while (true) {
    opcode = static_cast<Translation::Opcode>(it.Next());

    it.Skip(Translation::NumberOfOperandsFor(opcode));
    if (opcode == Translation::FRAME) {
      if (frames_to_skip == 0) {


        it.Skip(Translation::NumberOfOperandsFor(
            static_cast<Translation::Opcode>(it.Next())));

        for (int i = 0; i < args_slots->length(); ++i) {
          (*args_slots)[i] = ComputeSlotForNextArgument(&it, data, frame);
        }
        return;
      }
      frames_to_skip--;
    }
  }

  UNREACHABLE();
}
