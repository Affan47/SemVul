RunImpl() const
    {
		TestResults* testResults = TestRunnerFixture::s_testRunnerFixtureTestResults;

        for (int i=0; i < count; ++i)
        {
            if (asserted)
				Detail::ReportAssertEx(testResults, &m_details, "desc", "file", 0);
            else if (!success)
				testResults->OnTestFailure(m_details, "message");
        }
    }
