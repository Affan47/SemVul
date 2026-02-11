initOptions(ProgramOptions::OptionContext& root) {
	GlobalOptions* global = config;
	OptionGroup general("Clasp - General Options");
	general.addOptions()
		("configuration", notify(this, &GeneralOptions::mapDefaultConfig)->defaultsTo("frumpy"),
		 "Configure default configuration [%D]\n"
		 "      %A: {frumpy|jumpy|handy|crafty|trendy"
#if WITH_THREADS
		 "|chatty"
#endif
		 "}\n        frumpy: Use conservative defaults\n"
		 "        jumpy : Use aggressive defaults\n"
		 "        handy : Use defaults geared towards large problems\n"
		 "        crafty: Use defaults geared towards crafted problems\n"
		 "        trendy: Use defaults geared towards industrial problems\n"
#if WITH_THREADS
		 "        chatty: Use 4 competing threads initialized via the default portfolio\n"
#endif
		 )

		("solve-limit", storeTo(global->solve.limit, &GeneralOptions::parseSolveLimit)->arg("<n>[,<m>]"), "Stop search after <n> conflicts or <m> restarts\n")

		("enum-mode,e", storeTo(global->enumerate.mode, &mapEnum<enumModes>)->defaultsTo("auto")->state(Value::value_defaulted),
		 "Configure enumeration algorithm [%D]\n"
		 "      %A: {bt|record|brave|cautious|auto}\n"
		 "        bt      : Backtrack decision literals from solutions\n"
		 "        record  : Add nogoods for computed solutions\n"
		 "        brave   : Compute brave consequences (union of models)\n"
		 "        cautious: Compute cautious consequences (intersection of models)\n"
		 "        auto    : Use bt for enumeration and record for optimization")
		("number,n", storeTo(global->enumerate.numModels)->arg("<n>"), "Compute at most %A models (0 for all)")
		("restart-on-model"  , flag(global->enumerate.restartOnModel), "Restart after each model")
		("project"           , flag(global->enumerate.project)       , "Project models to named atoms in enumeration mode\n")
		("project-opt,@2", storeTo(global->enumerate.projectOpts), "Additional options for projection as octal digit")

		("opt-ignore"        , flag(global->opt.no) ,                  "Ignore optimize statements")
		("opt-sat"           , flag(global->enumerate.maxSat), "Treat DIMACS input as MaxSAT optimization problem")
		("opt-hierarch"      , storeTo(global->opt.hierarch)->arg("{0..3}")->implicit("1"),
		 "Process optimize statements in order of priority\n"
		 "    For each criterion use:\n"
		 "      1: fixed step size of one\n"
		 "      2: exponentially increasing step sizes\n"
		 "      3: exponentially decreasing step sizes")
		("opt-all"           , notify(this, &GeneralOptions::mapOptVal)->arg("<opt>..."), "Compute models <= %A")
		("opt-value"         , notify(this, &GeneralOptions::mapOptVal)->arg("<opt>..."), "Initialize objective function(s)\n")

		("sat-prepro,@1", notify(this, &GeneralOptions::mapSatPre)->implicit("-1"),
		 "Run SatELite-like preprocessing (Implicit: %I)\n"
		 "      %A: <n1>[,...][,<n5 {0..2}>] (-1=no limit)\n"
		 "        <n1>: Run for at most <n1> iterations\n"
		 "        <n2>: Run variable elimination with cutoff <n2>              [-1]\n"
		 "        <n3>: Run for at most <n3> seconds                           [-1]\n"
		 "        <n4>: Disable if <n4>%% of vars are frozen                    [-1]\n"
		 "        <n5>: Run blocked clause elimination  {0=no,1=limited,2=full} [1]")
		("learn-explicit,@1", notify(this, GeneralOptions::mapLearnExplicit)->flag(), "Do not use Short Implication Graph for learning")
	;
	OptionGroup asp("Clasp - ASP Options");
	asp.addOptions()
		("pre" , flag(global->enumerate.onlyPre), "Run ASP preprocessing and exit")
		("supp-models",flag(global->eq.noSCC), "Compute supported models (no unfounded set check)")
		("eq,@1", storeTo(global->eq.iters)->arg("<n>"), "Configure equivalence preprocessing\n"
		"      Run for at most %A iterations (-1=run to fixpoint)")
		("backprop!,@1",flag(global->eq.backprop), "Use backpropagation in ASP-preprocessing")
		("eq-dfs,@2"  , flag(global->eq.dfOrder)    , "Enable df-order in eq-preprocessing")
		("trans-ext!,@1", storeTo(global->eq.erMode, &mapEnum<extRules>),
		 "Configure handling of Lparse-like extended rules\n"
		 "      %A: {all|choice|card|weight|integ|dynamic}\n"
		 "        all    : Transform all extended rules to basic rules\n"
		 "        choice : Transform choice rules, but keep cardinality and weight rules\n"
		 "        card   : Transform cardinality rules, but keep choice and weight rules\n"
		 "        weight : Transform cardinality and weight rules, but keep choice rules\n"
		 "        integ  : Transform cardinality integrity constraints\n"
		 "        dynamic: Transform \"simple\" extended rules, but keep more complex ones")
	;
	root.add(general);
	root.add(asp);
}
