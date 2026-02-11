help(void) {
      std::cerr << '\t' << opt << " (string) default: "
                << ((cur == NULL) ? "NONE" : cur) << std::endl
                << "\t\t" << exp << std::endl;
    }
