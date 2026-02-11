initializeSyscallFailureSimulation(const char *processName) {


	const char *spec = getenv("PASSENGER_SIMULATE_SYSCALL_FAILURES");
	string prefix = string(processName) + "=";
	vector<string> components;
	unsigned int i;


	split(spec, ';', components);
	for (i = 0; i < components.size(); i++) {
		if (startsWith(components[i], prefix)) {

			string value = components[i].substr(prefix.size());
			split(value, ',', components);
			vector<string> keyAndValue;
			vector<ErrorChance> chances;


			for (i = 0; i < components.size(); i++) {
				split(components[i], ':', keyAndValue);
				if (keyAndValue.size() != 2) {
					fprintf(stderr, "%s: invalid syntax in PASSENGER_SIMULATE_SYSCALL_FAILURES: '%s'\n",
						processName, components[i].c_str());
					continue;
				}

				int e = lookupErrno(keyAndValue[0].c_str());
				if (e == -1) {
					fprintf(stderr, "%s: invalid error code in PASSENGER_SIMULATE_SYSCALL_FAILURES: '%s'\n",
						processName, components[i].c_str());
					continue;
				}

				ErrorChance chance;
				chance.chance = atof(keyAndValue[1].c_str());
				if (chance.chance < 0 || chance.chance > 1) {
					fprintf(stderr, "%s: invalid chance PASSENGER_SIMULATE_SYSCALL_FAILURES: '%s' - chance must be between 0 and 1\n",
						processName, components[i].c_str());
					continue;
				}
				chance.errorCode = e;
				chances.push_back(chance);
			}


			setup_random_failure_simulation(&chances[0], chances.size());
			return;
		}
	}
}
