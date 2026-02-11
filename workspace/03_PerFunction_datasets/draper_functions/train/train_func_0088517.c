RunImpl() const
        {
            TestResults& testResults_ = *CurrentTest::Results();

            for (int i=0; i < count; ++i)
            {
                if (asserted)
                {
                    ReportAssert("desc", "file", 0);
                }
                else if (!success)
                {
                    testResults_.OnTestFailure(m_details, "message");
                }
            }
        }
