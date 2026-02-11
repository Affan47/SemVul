Declare(Handle<String> name,
                               Variable::Mode mode,
                               FunctionLiteral* fun,
                               bool resolve,
                               bool* ok) {
  Variable* var = NULL;


  Scope* declaration_scope = mode == Variable::LET ? top_scope_
      : top_scope_->DeclarationScope();
  if (declaration_scope->is_function_scope() ||
      declaration_scope->is_strict_mode_eval_scope() ||
      declaration_scope->is_block_scope()) {

    var = declaration_scope->LocalLookup(name);
    if (var == NULL) {

      var = declaration_scope->DeclareLocal(name, mode);
    } else {


      if ((mode != Variable::VAR) || (var->mode() != Variable::VAR)) {

        ASSERT(var->mode() == Variable::VAR ||
               var->mode() == Variable::CONST ||
               var->mode() == Variable::LET);
        if (harmony_block_scoping_) {


          SmartArrayPointer<char> c_string = name->ToCString(DISALLOW_NULLS);
          const char* elms[2] = { "Variable", *c_string };
          Vector<const char*> args(elms, 2);
          ReportMessage("redeclaration", args);
          *ok = false;
          return NULL;
        }
        const char* type = (var->mode() == Variable::VAR) ? "var" :
                           (var->mode() == Variable::CONST) ? "const" : "let";
        Handle<String> type_string =
            isolate()->factory()->NewStringFromUtf8(CStrVector(type), TENURED);
        Expression* expression =
            NewThrowTypeError(isolate()->factory()->redeclaration_symbol(),
                              type_string, name);
        declaration_scope->SetIllegalRedeclaration(expression);
      }
    }
  }


  VariableProxy* proxy = declaration_scope->NewUnresolved(
      name, false, scanner().location().beg_pos);
  declaration_scope->AddDeclaration(
      new(zone()) Declaration(proxy, mode, fun, top_scope_));


  if (mode == Variable::CONST && declaration_scope->is_global_scope()) {
    ASSERT(resolve);
    Variable::Kind kind = Variable::NORMAL;
    var = new(zone()) Variable(declaration_scope,
                               name,
                               Variable::CONST,
                               true,
                               kind);
  }


  if (resolve && var != NULL) proxy->BindTo(var);

  return proxy;
}
