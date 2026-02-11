getXAxisLabels(struct AllData& alldata, vector<string>& xLabels) {
    if (grouped) {
        for (map<uint64_t, set<uint64_t> >::const_iterator it =
                alldata.grouping.groupsToProcesses.begin(); it
                != alldata.grouping.groupsToProcesses.end(); it++) {


            string procFrom = alldata.processIdNameMap[*(it->second.begin())];
            if (it->second.size() > 1) {
                string procTo =
                        alldata.processIdNameMap[*(it->second.rbegin())];
                procFrom = "\\shortstack[r]{" + procFrom + "\\\\" + "-\\\\"
                        + procTo + "}";
            }


            xLabels.push_back(procFrom);
        }
    } else {
        for (set<Process, ltProcess>::const_iterator it =
                alldata.allProcesses.begin(); it != alldata.allProcesses.end(); it++) {
            xLabels.push_back(alldata.processIdNameMap[it->process]);
        }
    }
}
