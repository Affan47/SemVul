setStage(int stage)
{
    m_stage = stage;

    rootObject()->setProperty("stage", stage);
}
