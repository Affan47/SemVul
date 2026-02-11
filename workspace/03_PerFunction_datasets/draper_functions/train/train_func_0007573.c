ShowResults() const
{
    TimerResultsData overallData;

    std::map<std::string, struct TimerResultsData>::const_iterator I = _results.begin();
    const std::map<std::string, struct TimerResultsData>::const_iterator E = _results.end();

    while (I != E) {
        const double sec = I->second.seconds();
        const double secAverage = sec / (double)(I->second._numberOfResults);
        std::cout << I->first << ": " << sec << "s (avg. " << secAverage << "s - " << I->second._numberOfResults  << " result(s))" << std::endl;

        overallData._clocks += I->second._clocks;

        ++I;
    }

    const double secOverall = overallData.seconds();
    std::cout << "Overall time: " << secOverall << "s" << std::endl;
}
