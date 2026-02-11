CompleteArch(std::string const &arch) {
	if (arch.find('-') != std::string::npos) {

		std::string complete = std::string("-").append(arch).append("-");
		complete = SubstVar(complete, "-any-", "-*-");
		complete = complete.substr(1, complete.size()-2);
		return complete;
	}
	else if (arch == "any")			return "*-*";
	else					return "linux-" + arch;
}
