VisitJSFunctionAndFlushCode(Map* map, HeapObject* object) {
    JSFunction* jsfunction = reinterpret_cast<JSFunction*>(object);

    bool flush_code_candidate = false;
    if (IsValidNotBuiltinContext(jsfunction->unchecked_context())) {
      flush_code_candidate = FlushCodeForFunction(jsfunction);
    }

    if (!flush_code_candidate) {
      MarkCompactCollector::MarkObject(
          jsfunction->unchecked_shared()->unchecked_code());

      if (jsfunction->unchecked_code()->kind() == Code::OPTIMIZED_FUNCTION) {


        DeoptimizationInputData* data =
            reinterpret_cast<DeoptimizationInputData*>(
                jsfunction->unchecked_code()->unchecked_deoptimization_data());

        FixedArray* literals = data->UncheckedLiteralArray();

        for (int i = 0, count = data->InlinedFunctionCount()->value();
             i < count;
             i++) {
          JSFunction* inlined = reinterpret_cast<JSFunction*>(literals->get(i));
          MarkCompactCollector::MarkObject(
              inlined->unchecked_shared()->unchecked_code());
        }
      }
    }

    VisitJSFunctionFields(map,
                          reinterpret_cast<JSFunction*>(object),
                          flush_code_candidate);
  }
