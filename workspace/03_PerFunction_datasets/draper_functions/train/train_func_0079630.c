showOptionalHelp(nor_utils::Args& args)
{
	string helpType = args.getValue<string>("h", 0);

	cout << "MultiBoost (v" << CURRENT_VERSION << "). An obvious name for a multi-class AdaBoost learner." << endl;
	cout << "---------------------------------------------------------------------------" << endl;

	if (helpType == "general")
		args.printGroup("General Options");
	else if (helpType == "io")
		args.printGroup("I/O Options");
	else if (helpType == "algo")
		args.printGroup("Basic Algorithm Options");
	else if (helpType == "bandits")
		args.printGroup("Bandit Algorithm Options");
	else if (helpType == "vjcascade")
		args.printGroup("Viola-Jones Cascade Algorithm Options");
	else if (helpType == "softcascade")
		args.printGroup("SoftCascade Algorithm Options");
	else if ( BaseLearner::RegisteredLearners().hasLearner(helpType) )
		args.printGroup(helpType + " Options");
	else
		cerr << "ERROR: Unknown help section <" << helpType << ">" << endl;
}
