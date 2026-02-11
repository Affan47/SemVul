elements() const {
      return new MakeEnumeration<Parms, StringEnumeration>
	(suggestions.begin(), Parms(suggestions.end()));
    }
  }
