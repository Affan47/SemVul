query (void)
    {
      if (this->monitor_ == 0)
        {
          ACE_ERROR ((LM_ERROR, "Monitor_Query::query - null monitor\n"));
          return;
        }

      Monitor_Base::CONSTRAINTS& list = this->monitor_->constraints ();

      for (Monitor_Base::CONSTRAINT_ITERATOR i (list.begin ());
           i != list.end ();
           ++i)
        {
          Constraint_Interpreter interpreter;
          interpreter.build_tree (i->second.expr.fast_rep ());

          Monitor_Control_Types::Data data (this->monitor_->type ());
          this->monitor_->retrieve (data);
          Constraint_Visitor visitor (data);
          bool satisfied = interpreter.evaluate (visitor);

          if (satisfied && i->second.control_action != 0)
            {
              i->second.control_action->execute ();
            }
        }
    }
