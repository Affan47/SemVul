showManual()
{
    const QString title = Types::cleanString(QCoreApplication::translate("Help", "&Manual"));
    QString manual = QString(QLatin1String("<h1>%1</h1>")).arg(title);
    manual.append(Types::newlineToParagraph(QCoreApplication::translate("Help",
        "PosteRazor has its user interface organized in a 'Wizard' fashion. All settings for the poster creation can be done in %1 steps.\n"
        "The <b>%2</b> and <b>%3</b> buttons navigate through these steps. The <b>?</b> button opens a help window with an explanation of the current step.\n"
        "All entries and choices are remembered until the next usage of the PosteRazor.",
        "Manual preface. Place holders: %1 = Number of wizard steps, %2 = 'Back', %3 = 'Next' (will be automatically inserted)")
        .arg(wizardStepsCount() - m_unavaliableSteps.count())
        .arg(QCoreApplication::translate("Main window", "Back"))
        .arg(QCoreApplication::translate("Main window", "Next"))));
    for (int i = 0; i < wizardStepsEnum().keyCount(); i++) {
        const WizardSteps step = (WizardSteps)wizardStepsEnum().value(i);
        if (!m_unavaliableSteps.contains(step)){
            manual.append(QString(QLatin1String("<h2>%1</h2>")).arg(stepTitle(step)));
            manual.append(stepHelp(step));
        }
    }

    emit showManualSignal(title, manual);
}
