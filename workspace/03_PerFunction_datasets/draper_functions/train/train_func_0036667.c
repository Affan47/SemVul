LoadConnections(int alias, bool full_name)
{
    list<pair<string, pair<string, string> > >::const_iterator it;

    if (full_name) {
        for (it = fConnections.begin(); it != fConnections.end(); it++) {
            pair<string, string> connection = (*it).second;
            jack_info("Load connection: %s %s", connection.first.c_str(), connection.second.c_str());
            fEngine->PortConnect(fClientControl.fRefNum, connection.first.c_str(), connection.second.c_str());
        }
    } else {
        const char** inputs = fGraphManager->GetPorts(NULL, NULL, JackPortIsInput);
        const char** outputs = fGraphManager->GetPorts(NULL, NULL, JackPortIsOutput);

        for (it = fConnections.begin(); it != fConnections.end(); it++) {
            pair<string, string> connection = (*it).second;
            string real_input = MatchPortName(connection.first.c_str(), outputs, alias, (*it).first);
            string real_output = MatchPortName(connection.second.c_str(), inputs, alias, (*it).first);
            if ((real_input != "") && (real_output != "")) {
                jack_info("Load connection: %s %s", real_input.c_str(), real_output.c_str());
                fEngine->PortConnect(fClientControl.fRefNum, real_input.c_str(), real_output.c_str());
            }
        }


        if (fGraphManager->IsPendingChange()) {
            JackSleep(int(fEngineControl->fPeriodUsecs * 1.1f));
        }

        if (inputs) {
            free(inputs);
        }
        if (outputs) {
            free(outputs);
        }
    }
}
