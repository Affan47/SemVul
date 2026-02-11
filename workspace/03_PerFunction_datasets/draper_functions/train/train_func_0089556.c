moveBack(Score & currentScore, int index, QList<NetOrdering> & allOrderings) {
    if (index == 0) {
        return false;
    }

    QList<int> order(currentScore.ordering.order);

    int netIndex = order.takeAt(index);

    for (int i = index - 1; i >= 0; i--) {
        bool done = true;
        order.insert(i, netIndex);

        foreach (NetOrdering ordering, allOrderings) {
            bool gotOne = true;
            for (int j = 0; j < order.count(); j++) {
                if (order.at(j) != ordering.order.at(j)) {
                    gotOne = false;
                    break;
                }
            }
            if (gotOne) {
                done = false;
                break;
            }
        }
        if (done == true) {
            NetOrdering newOrdering;
            newOrdering.order = order;
            allOrderings.append(newOrdering);


            return true;
        }
        order.removeAt(i);
    }

    return false;
}
