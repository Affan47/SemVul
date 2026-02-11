HandlePolymorphicLoadNamedField(Property* expr,
                                                    HValue* object,
                                                    ZoneMapList* types,
                                                    Handle<String> name) {
  int number_of_types = Min(types->length(), kMaxLoadPolymorphism);
  ZoneMapList maps(number_of_types);
  ZoneList<HSubgraph*> subgraphs(number_of_types);
  bool needs_generic = (types->length() > kMaxLoadPolymorphism);


  for (int i = 0; i < number_of_types; ++i) {
    Handle<Map> map = types->at(i);
    LookupResult lookup;
    map->LookupInDescriptors(NULL, *name, &lookup);
    if (lookup.IsProperty() && lookup.type() == FIELD) {
      HSubgraph* subgraph = CreateBranchSubgraph(environment());
      SubgraphScope scope(this, subgraph);
      HLoadNamedField* instr =
          BuildLoadNamedField(object, expr, map, &lookup, false);
      instr->set_position(expr->position());
      instr->ClearFlag(HValue::kUseGVN);
      PushAndAdd(instr);
      maps.Add(map);
      subgraphs.Add(subgraph);
    } else {
      needs_generic = true;
    }
  }


  if (maps.length() == 0) {
    HInstruction* instr = BuildLoadNamedGeneric(object, expr);
    instr->set_position(expr->position());
    ast_context()->ReturnInstruction(instr, expr->id());
  } else {

    HSubgraph* default_graph = CreateBranchSubgraph(environment());
    { SubgraphScope scope(this, default_graph);
      if (!needs_generic && FLAG_deoptimize_uncommon_cases) {
        default_graph->exit_block()->FinishExit(new HDeoptimize());
        default_graph->set_exit_block(NULL);
      } else {
        HInstruction* instr = BuildLoadNamedGeneric(object, expr);
        instr->set_position(expr->position());
        PushAndAdd(instr);
      }
    }

    HBasicBlock* new_exit_block =
        BuildTypeSwitch(object, &maps, &subgraphs, default_graph, expr->id());
    set_current_block(new_exit_block);


    if (current_block() != NULL && !ast_context()->IsEffect()) {
      ast_context()->ReturnValue(Pop());
    }
  }
}
