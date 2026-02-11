declareArguments(nor_utils::Args& args)
	{
		AbstainableLearner::declareArguments(args);

		args.declareArgument("rsample",
							 "Instead of searching for a featurewise in all the possible dimensions (features), select a set of "
							 " size <num> of random dimensions. "
							 "Example: -rsample 50 -> Search over only 50 dimensions"
							 "(Turned off for Haar: use -csample instead)",
							 1, "<num>");

	}
