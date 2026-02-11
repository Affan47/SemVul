appendReallocIntegrity() {
        KDevVarLengthArray<TestValue, 2> array;
        QCOMPARE(array.size(), 0);
        QCOMPARE(array.capacity(), 2);

        qDebug() << "append item 1";
        array << TestValue();
        qDebug() << "appended index is:" << array[0].m_index;
        QCOMPARE(array.size(), 1);
        QCOMPARE(array.capacity(), 2);
        qDebug() << "append item 2";
        array << TestValue();
        qDebug() << "appended index is:" << array[1].m_index;
        QCOMPARE(array.size(), 2);
        QCOMPARE(array.capacity(), 2);
        qDebug() << "append item 3";
        array << TestValue();
        qDebug() << "appended index is:" << array[2].m_index;
        QCOMPARE(array.size(), 3);
        QCOMPARE(array.capacity(), 4);

        array.clear();
    }
}
