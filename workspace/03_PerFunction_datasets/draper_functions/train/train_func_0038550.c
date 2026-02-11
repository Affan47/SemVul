print() const
{
    int count[TestOutcome::LAST];
    int expected[TestOutcome::LAST];
    for( int i = 0; i < TestOutcome::LAST; ++i ) {
        count[i] = 0;
        expected[i] = 0;
    }


    for (const_iterator it(begin()); it != end(); ++it) {
        ++count[it->severity];
        if (it->expected) ++expected[it->severity];
        if ((it->severity != TestOutcome::PASSED || OsiUnitTest::verbosity >= 2) &&
                (it->severity != TestOutcome::NOTE || OsiUnitTest::verbosity >= 1))
            it->print();
    }

    for (int i = 0; i < TestOutcome::LAST; ++i)
        printf("Severity %-10s: %4d  thereof expected: %4d\n",
               TestOutcome::SeverityLevelName[i].c_str(), count[i], expected[i]);
}
