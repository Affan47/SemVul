createCategoryTree(const QVector<CategoryItem *> &cats) const
{
    QList<CategoryItem *> toReturn;

    for(int i = 0; i < cats.count(); ++i) {
        CategoryItem *parent = cats.at(i);
        int id = parent->id();


        for(int j = 0; j < cats.count(); ++j) {
            CategoryItem *child = cats.at(j);

            if (child->parentId() == id) {
                if (parent->children().contains(child))
                    continue;

                parent->addChild(child);

            }
        }

        if (parent->parentId() < 0) {
            toReturn << parent;
        }
        parent->sortChildren();
    }


    qSort(toReturn.begin(), toReturn.end(), CategoryItem::lessThan);

    return toReturn;
}
