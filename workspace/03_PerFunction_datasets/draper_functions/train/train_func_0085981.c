updateAction(ActionTools::ActionInstance *actionInstance, const Tools::Version &version) const
{

    if(version < Tools::Version(1, 1, 0))
    {
        const ActionTools::ExceptionActionInstancesHash &exceptions = actionInstance->exceptionActionInstances();

        if(exceptions.contains(static_cast<ActionTools::ActionException::Exception>(FindImageInstance::CannotFindTheImageException)))
        {
            const ActionTools::ActionException::ExceptionActionInstance &exceptionAction = exceptions.value(static_cast<ActionTools::ActionException::Exception>(FindImageInstance::CannotFindTheImageException));
            ActionTools::Parameter ifNotFoundParameter = actionInstance->parameter("ifNotFound");

            switch(exceptionAction.action())
            {
            case ActionTools::ActionException::StopExecutionExceptionAction:
                ifNotFoundParameter.setSubParameter("action", false, ActionTools::IfActionParameterDefinition::actions.first[ActionTools::IfActionParameterDefinition::RunCode]);
                ifNotFoundParameter.setSubParameter("line", true, "Console.printError(\"Script line \" + Script.line + \": Cannot find the image\");\nExecution.stop();");
                break;
            case ActionTools::ActionException::SkipExceptionAction:
                ifNotFoundParameter.setSubParameter("action", false, ActionTools::IfActionParameterDefinition::actions.first[ActionTools::IfActionParameterDefinition::DoNothing]);
                break;
            case ActionTools::ActionException::GotoLineExceptionAction:
                ifNotFoundParameter.setSubParameter("action", false, ActionTools::IfActionParameterDefinition::actions.first[ActionTools::IfActionParameterDefinition::Goto]);
                ifNotFoundParameter.setSubParameter("line", false, exceptionAction.line());
                break;
            default:
                break;
            }

            actionInstance->setParameter("ifNotFound", ifNotFoundParameter);
        }
    }
}
